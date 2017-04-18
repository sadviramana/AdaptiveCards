using AdaptiveCards.Rendering.Options;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AdaptiveCards.Rendering
{

    public abstract class AdaptiveRenderer<TUIElement, TContext>
        where TUIElement : class
        where TContext : class
    {
        protected AdaptiveRenderer(HostOptions options)
        {
            DefaultOptions = options ?? new HostOptions();
        }

        public HostOptions DefaultOptions { get; set; }

        public Dictionary<Type, Func<TypedElement, TContext, TUIElement>> ElementRenderers = new Dictionary<Type, Func<TypedElement, TContext, TUIElement>>();

        public void SetRenderer<TElement>(Func<TypedElement, TContext, TUIElement> renderer)
        {
            ElementRenderers[typeof(TElement)] = renderer;
        }
    }
}